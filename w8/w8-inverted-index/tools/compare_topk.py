from __future__ import annotations

import argparse
import csv
import math
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class Row:
    rank: int
    document_id: int
    score: float


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Compare C++ and Python Top-K TSV outputs."
    )
    parser.add_argument("--cpp", type=Path, required=True)
    parser.add_argument("--python", type=Path, required=True)
    parser.add_argument("--tolerance", type=float, default=1e-9)
    return parser.parse_args()


def load_results(path: Path) -> dict[str, list[Row]]:
    grouped: dict[str, list[Row]] = defaultdict(list)
    with path.open("r", encoding="utf-8", newline="") as file:
        reader = csv.DictReader(file, delimiter="\t")
        expected = ["query", "rank", "doc_id", "score"]
        if reader.fieldnames != expected:
            raise ValueError(f"{path}: unexpected columns {reader.fieldnames}")

        for line_number, row in enumerate(reader, start=2):
            try:
                grouped[row["query"]].append(
                    Row(
                        rank=int(row["rank"]),
                        document_id=int(row["doc_id"]),
                        score=float(row["score"]),
                    )
                )
            except (KeyError, ValueError) as error:
                raise ValueError(
                    f"{path}:{line_number}: invalid row: {error}"
                ) from error

    for rows in grouped.values():
        rows.sort(key=lambda item: item.rank)
    return dict(grouped)


def main() -> int:
    args = parse_args()
    cpp = load_results(args.cpp)
    python = load_results(args.python)

    queries = sorted(cpp.keys() | python.keys())
    errors = []
    checked = 0

    for query in queries:
        cpp_rows = cpp.get(query, [])
        python_rows = python.get(query, [])
        if len(cpp_rows) != len(python_rows):
            errors.append(
                f"{query!r}: row count C++={len(cpp_rows)} "
                f"Python={len(python_rows)}"
            )
            continue

        for cpp_row, python_row in zip(cpp_rows, python_rows):
            if cpp_row.rank != python_row.rank:
                errors.append(
                    f"{query!r}: rank mismatch "
                    f"C++={cpp_row.rank} Python={python_row.rank}"
                )
            if cpp_row.document_id != python_row.document_id:
                errors.append(
                    f"{query!r} rank {cpp_row.rank}: doc id mismatch "
                    f"C++={cpp_row.document_id} "
                    f"Python={python_row.document_id}"
                )
            if not math.isfinite(cpp_row.score) or not math.isfinite(python_row.score):
                errors.append(f"{query!r} rank {cpp_row.rank}: non-finite score")
            elif abs(cpp_row.score - python_row.score) > args.tolerance:
                errors.append(
                    f"{query!r} rank {cpp_row.rank}: score mismatch "
                    f"C++={cpp_row.score:.17g} "
                    f"Python={python_row.score:.17g}"
                )
            checked += 1

    if errors:
        print(f"FAIL: {len(errors)} difference(s)")
        for error in errors[:30]:
            print(error)
        return 1

    print(f"PASS: {len(queries)} queries, {checked} result rows matched")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
