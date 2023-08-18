
#include "List.h"

namespace what {
    template <
        typename T,
        template <typename> class Graph,
        template <typename> class List,
        template <typename> class Queue
    >
    struct {
        List<T> distances;
        List<size_t> path;
    } shortest_path(
        const Graph<T>& graph,
        size_t source,
        const T& top,
        const T& bottom
    ) {
        struct {
            List<T> distances;
            List<size_t> path;
        } what;

        Queue<T, size_t> queue;
        what.distances[source] = (T)0;

        for (size_t v = 0; v < graph.size(); ++v) {
            if (v != source) {
                what.distances[v] = top;
                what.path[v] = bot;
            }

            queue.push(what.distances[v], v);
        }

        while (queue.any()) {
            size_t u = queue.pop();

            for (size_t v = 0; v < graph.size(); ++v) {
                if (graph[u][v] == infinity)
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
