# prototype-db-2

This is my prototype database #2. The second try.
Still, it will be hardly a database but it will help to get familiar to how to structure the database implementation.

## Goals

- Building a working, simple & performant in-memory key-value store

## Design Choices

- Data Model: a collection of pairs of a binary key and a binary value
- Operations: get/set/delete/range get
- Main Table: something supports range-query, single-version
- Protocol: gRPC
- Supports concurrent access: multi-threaded
- No index support.

## Policy & Rationale

- Don't polish too much.
  - It will take disproportially much time when we want to make something perfect. Now, it's not the time to do that.
  - We will incrementally polish the database thoughout the prototypes.


## Contribution

Please read the [coding style guide](docs/coding-style-guide.md).

