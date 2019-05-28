#ifndef UTILS_H
#define UTILS_H

template <class T>
static void clear_vector(const vector<T> &v) {
    for(int i = 0; i < v.size(); i++) {
        if (v[i] != NULL) {
            delete v[i];
        }
    }
}

#endif // UTILS_H
