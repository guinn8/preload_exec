# Build System Capture

Alias `exec` to capture compiler invocations during a build.

## Compile the Shared Library

```shell
gcc -shared -fPIC -o preload_exec.so preload_exec.c -ldl
```

## Use the Preload Library to Track Compiler Invocations

```shell
export LD_PRELOAD=/path/to/preload_exec.so
```

While that envvar is exported when you `make` (or otherwise build) all `exec` syscalls invoking any `gcc` will be saved to `/tmp/compile.log`.
