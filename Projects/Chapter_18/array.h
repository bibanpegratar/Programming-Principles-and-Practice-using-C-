template <typename T, int N>
struct array
{
    T elem[N];

    T& operator[] (int n) { return elem[n]; }
    const T& operator[] (int n) const { return elem[n]; };

    T* data() { return elem; }
    const T* data() const { return elem; }

    int size() { return N; }
};

