#pragma once
#include <vector>
using std::vector;
namespace mybitset
{	
	template <size_t N>
	class bitset
	{
	public:
		bitset()
			: _bit((N>>3)+1), _bitCount(N)
		{}
		// ��which����λ��1
		void set(size_t which, bool t = 1)
		{	
			size_t n = which / (sizeof(char)*8);
			size_t i =which % (sizeof(char) * 8);
			if(t==1)
				_bit[n] |= (1 << i);
			else
				_bit[n] &= ~(1 << i);
		}
			// ��which����λ��0
		void reset(size_t which)
		{
			set(which, 0);
		}
			// ���λͼ��which�Ƿ�Ϊ1
		bool test(size_t which)
		{
			size_t n = which / (sizeof(char) * 8);
			size_t i = which % (sizeof(char) * 8);
			bool w = (_bit[n] >> i) & 1;
			return w;
		}
		size_t size()const { return _bitCount; }

	private:
		vector<char> _bit;
		size_t _bitCount;
	};
}