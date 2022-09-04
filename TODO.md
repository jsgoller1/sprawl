# TODO
- Set up compilation via Bazel
    - Integrate gtest with Bazel (easy, see Omerta)
    - Integrate SDL2 with Bazel (hard)
        - Tried using system install via apt-get, didn't know how to include all headers, .a, and .so files
            - Can likely get this working with more time
        - Tried building SDL2 source in local directory and including it as external repo
        - Tried using https://github.com/bazelregistry/sdl2, didn't build
        - If system install doesn't work well, might be a good idea to copy repo and bazel-ify it for inclusion via http archive like gtest
