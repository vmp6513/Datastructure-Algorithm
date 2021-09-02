#include <exception>

template <typename T>
class vector {
   private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void resize(size_t new_capacity) {
        // new capacity must bigger than m_capacity
        if (new_capacity < m_capacity) return;
        T* tmp = m_data;
        m_data = new T[new_capacity];
        for (int i = 0; i < m_capacity; i++) m_data[i] = tmp[i];

        m_capacity = new_capacity;
        delete[] tmp;
    }

   public:
    vector() : m_data(nullptr), m_size(0), m_capacity(0) {}
    vector(size_t size = 1) {
        if (size <= 0) throw std::exception();
        m_size = size;
        m_capacity = 2 * size;
        m_data = new T[m_capacity];
    }
    ~vector() { delete[] m_data; }
    bool empty() const { return m_size == 0; }
    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    void push_back(const T& val) {
        if (m_data == nullptr) {
            m_capacity = 2;
            m_data = new T[m_capacity];
        }
        if (m_size == m_capacity) {
            resize(2 * m_capacity);
        }
        m_data[m_size] = val;
        m_size++;
    }
    void pop_back() {
        if (m_size == 0) {
            throw std::exception();
        }
        m_size--;
    }
    T operator[](size_t index) const {
        if (index < 0 || index >= m_size) {
            throw std::exception();
        }
        return m_data[index];
    }
};
