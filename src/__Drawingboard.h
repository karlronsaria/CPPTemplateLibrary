
#include "Array.h"
#include "List.h"
#include "Matrix.h"

namespace what {
    template <typename T>
    struct PathTable {
        Array<T> distances;
        Array<size_t> path;
    };

    template <typename T>
    PathTable<T>
    shortest_path(
        const Matrix<T>& graph,
        size_t source,
        const T& top,
        const T& bottom
    ) {
        PathTable<T>
		what;

        Queue<T, size_t>
		queue;

        what.distances.resize(graph.size());
        what.path.resize(graph.size());
        what.distances[source] = (T)0;

        for (size_t v = 0; v < graph.size(); ++v) {
            if (v != source) {
                what.distances[v] = top;
                what.path[v] = bottom;
            }

            queue.push(what.distances[v], v);
        }

        while (queue.any()) {
            size_t u = queue.pop();

            for (size_t v = 0; v < graph.size(); ++v) {
                if (graph[u][v] == top)
                    continue;

                T alt = what.distances[v] + graph[u][v];

                if (alt < what.distances[v]) {
                    T temp = what.distances[v];
                    what.distances[v] = alt;
                    what.path[v] = u;
                    queue.remove(temp);
                    queue.push(alt, v);
                }
            }
        }

        return what;
    }
}
