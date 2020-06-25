#include "graph.hpp"
#include <iostream>


int main() {
  Graph g{false};

  auto a = g.add({"a"});
  auto b = g.add({"b"});
  auto c = g.add({"c"});
  auto d = g.add({"d"});
  auto e = g.add({"e"});
  auto f = g.add({"f"});

  a->connect(e, 7);
  a->connect(f, 5);

  b->connect(a, 1);
  b->connect(c, 3);

  c->connect(d, 9);

  d->connect(e, 2);
  d->connect(f, 1);

  e->connect(b, 2);
  e->connect(c, 4);

  f->connect(e, 2);

  g.prim();
  g.print(std::cout);
}
