# TODO
- [x] Set up CMake
- [x] Set up linter/tidy
- [ x ] Make disassembler
    - [x] Extract metadata
        - [ ] [CBOR](https://en.wikipedia.org/wiki/CBOR) implementation
        - [ ] IPFS/Swarm resolution (?), might help with analysis for contracts with verifiable ABIs
    - [x] Extract Opcodes
    - [x] Optimize
        - [x] Being string heavy makes it very slow. Convert string to bytes right at initialization
        - [x] Do the same thing but with a vector of bytes (4head)
- [ ] [CFG](https://en.wikipedia.org/wiki/Control-flow_graph) Impl
    - [ ] Directed graph, use adjacency list
    - [ ] Use existing calldata from tx's to better define behavior (?)

# ISSUES

# MAYBE?