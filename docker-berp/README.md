
# Docker container to run Berp

To use this container run from the root of the gherkin repository:

```plain
docker build -t berp-env docker-berp/ && docker run --rm -ti -v "$PWD:/app" berp-env
```

to start the container. The `/app` directory in the container corresponds to the
repository root.


From there, `berp` is installed in your `$PATH`, meaning you should be able to run

```
make generate
```

in the project root or in your language folder.
