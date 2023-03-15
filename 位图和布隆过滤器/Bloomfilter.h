#pragma once
#include "mybitset.h"
#include <string>
using std::string;
namespace mybitset
{   
    struct BKDRHash
    {
        size_t operator()(const string& s)
        {
            // BKDR
            size_t value = 0;
            for (auto ch : s)
            {
                value *= 31;
                value += ch;
            }
            return value;
        }
    };
    struct APHash
    {
        size_t operator()(const string& s)
        {
            size_t hash = 0;
            for (long i = 0; i < s.size(); i++)
            {
                if ((i & 1) == 0)
                {
                    hash ^= ((hash << 7) ^ s[i] ^ (hash >> 3));
                }
                else
                {
                    hash ^= (~((hash << 11) ^ s[i] ^ (hash >> 5)));
                }
            }
            return hash;
        }
    };
    struct DJBHash
    {
        size_t operator()(const string& s)
        {
            size_t hash = 5381;
            for (auto ch : s)
            {
                hash += (hash << 5) + ch;
            }
            return hash;
        }
    };
    // 假设布隆过滤器中元素类型为K，每个元素对应5个哈希函数
    template<size_t N,size_t Times=5, class HashFunc1 = BKDRHash, class HashFunc2 = APHash,
        class HashFunc3 = DJBHash>
    class BloomFilter
    {
    public:
        BloomFilter()  // 布隆过滤器中元素个数
            :_bmp(), _size(0),capacity(N*Times)
        {}

        // 插入数据
        bool Insert(const string& key)
        {
            size_t key1= HashFunc1()(key)%capacity;
            size_t key2=HashFunc2()(key) % capacity;
            size_t key3=HashFunc3()(key) % capacity;
            if (_bmp.test(key1) && _bmp.test(key2) && _bmp.test(key3))
                return false;
            _bmp.set(key1);
            _bmp.set(key2);
            _bmp.set(key3);
            _size++;
            return true;
        }
        // 检测在不在
        bool IsInBloomFilter(const string& key)
        {
            size_t key1 = HashFunc1()(key) % capacity;
            size_t key2 = HashFunc2()(key) % capacity;
            size_t key3 = HashFunc3()(key) % capacity;
            if (_bmp.test(key1) && _bmp.test(key2) && _bmp.test(key3))
                return true;
            else
                return false;
        }
            // 布隆过滤器不支持删除
    private:
        bitset<N*Times> _bmp;
        size_t _size;   // 实际元素的个数
        size_t capacity;
    };
}