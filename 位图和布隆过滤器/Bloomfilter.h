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
    // ���貼¡��������Ԫ������ΪK��ÿ��Ԫ�ض�Ӧ5����ϣ����
    template<size_t N,size_t Times=5, class HashFunc1 = BKDRHash, class HashFunc2 = APHash,
        class HashFunc3 = DJBHash>
    class BloomFilter
    {
    public:
        BloomFilter()  // ��¡��������Ԫ�ظ���
            :_bmp(), _size(0),capacity(N*Times)
        {}

        // ��������
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
        // ����ڲ���
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
            // ��¡��������֧��ɾ��
    private:
        bitset<N*Times> _bmp;
        size_t _size;   // ʵ��Ԫ�صĸ���
        size_t capacity;
    };
}