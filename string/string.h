#include <bits/stdc++.h>
using namespace std;

// 字符串分割函数
void split(const string& str, vector<string>& arr,
           const string& delimiters = " ") {
    size_t left_pos = str.find_first_not_of(delimiters, 0);
    size_t right_pos = str.find_first_of(delimiters, left_pos);

    while (left_pos != str.npos || right_pos != str.npos) {
        arr.push_back(str.substr(left_pos, right_pos - left_pos));
        left_pos = str.find_first_not_of(delimiters, right_pos);
        right_pos = str.find_first_of(delimiters, left_pos);
    }
}

// memcpy，重点是考虑内存重叠

void* memcpy(void* dest, const void* src, size_t count) {
    if(dest == NULL || src == NULL)
        return NULL;
    char* p_dest = static_cast<char*>(dest);
    const char* p_src = static_cast<const char*>(src);
    
    // 重叠了
    if(p_dest > p_src && p_dest < p_src + count) {
        for(size_t i = count - 1; i >= 0; i--) {
            p_dest[i] = p_src[i];
        }
    }
    else {
        for(size_t i = 0; i < count; i++) {
            p_dest[i] = p_src[i];
        }
    }
    return dest;
}

// strcpy, 重点是返回值的类型

char* strcpy(char* dst, const char* src) {
    char* p = NULL;
    if(dst == NULL || src == NULL) 
        return NULL;

    p = dst;
    while((*(p++)=*(src++)) != '\0');
    return dst;
}

// strstr, 主要是各个指针的含义

char* strstr(const char* src, const char* target) {
    if(src == NULL || target == NULL) {
        return NULL;
    }

    const char* ret = src;
    const char* p_target = target;
    const char* p_src = NULL;

    while(*ret != '\0') {
        p_src = ret;
        p_target = target;
        while(*p_src != '\0' && *p_target != '\0' && *p_src == *p_target) {
            p_src++;
            p_target++;
        }
        if(*p_target == '\0')
            return const_cast<char*>(ret);
        else 
            ret++;
    }
    return NULL;
}
