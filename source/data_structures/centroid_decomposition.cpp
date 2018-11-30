vi g[MAXN];
int size[MAXN];
bool used[MAXN];

int get_size(int v, int p)
{
	size[v] = 1;
	for (auto to : g[v])
		if (!used[to] && to != p)
			size[v] += get_size(to, v);
	return size[v];
}

int findCentroid(int v, int p, int sz)
{
	for (auto to : g[v])
		if (!used[to] && to != p && 2 * size[to] > sz)
			return findCentroid(to, v, sz);
	return v;
}

void build(int v)
{
	int tree_size = get_size(v, -1);
	v = findCentroid(v, -1, sz);
	process(v); // например, в этой функции можно запомнить для каждой вершинки компоненты центроид v
	used[v] = true;
	for (auto to : g[v])
		if (!used[to])
			build(to);
}