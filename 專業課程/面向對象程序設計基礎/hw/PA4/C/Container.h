
template<typename T> class Container{
    struct message{
        int x, y;
        T id;
    };
    message* cont;
    int count;
public:
    Container() {
        cont = new message[1010];
        count = 0;
    };

    void insert(int x, int y, T id) {
        cont[count].x = x;
        cont[count].y = y;
        cont[count].id = id;
        count++;
    }

    T* find(int x, int y) {
        T* t = nullptr;
        for (int i = 0; i < count; i++) 
        if (cont[i].x == x && cont[i].y == y) {
            t = &cont[i].id;
            break;
        }
        return t;
    };

    ~Container() {
        delete[] cont;
    }
};