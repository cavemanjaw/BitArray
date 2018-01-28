#include <gtest/gtest.h>
#include "BitArray.h"

//Remove if will be not necessary
#include <iostream>

class BitArray_static_test : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(BitArray_static_test, DummyTest_static)
{
	BitArray<4, 5, false> bitArray;

	(void)bitArray;

	for (int i = 0; i < 4; ++i)
	{
		bitArray.Set(i, i * 2);
	}

	for (int i = 0; i < 4; ++i)
	{
		EXPECT_EQ(i * 2, bitArray.Get(i));
	}


	const unsigned numberOfArrayElements = 100;

	/*
	 * First, test all of the possible number of bits cases with one, the same literal insertion
	 */

	//One bit per element
	{
		BitArray<100, 1, false> bitArray;

		for (unsigned i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 1);
		}

		for (unsigned i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(1, bitArray.Get(i));
		}
	}
}

TEST_F(BitArray_static_test, Setting_and_getting_not_power_of_two_bits_1_3)
{
	constexpr unsigned numberOfArrayElements = 20;

	/*
	 * First, test all of the possible number of bits cases with one, the same literal insertion
	 */

	//Smashing stack? Why {} does not control the lifetime of objects?
	//One bit per element
	{
		BitArray<numberOfArrayElements, 1, false> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 1);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(1, bitArray.Get(i));
		}
	}

	//Three bits per element
	{
		BitArray<numberOfArrayElements, 3, false> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 7);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(7, bitArray.Get(i));
		}
	}

//TODO: Write the following test cases
}

TEST_F(BitArray_static_test, Setting_and_getting_not_power_of_two_bits_5_13)
{
	constexpr unsigned numberOfArrayElements = 20;
	//Five bits per element
	{
		BitArray<numberOfArrayElements, 5, false> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 31);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(31, bitArray.Get(i));
		}
	}

	//Seven bits per element
	{
		BitArray<numberOfArrayElements, 7, false> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 127);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(127, bitArray.Get(i));
		}
	}

	//Nine bits per element
	{
		BitArray<numberOfArrayElements, 9, false> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 511);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(511, bitArray.Get(i));
		}
	}

	//Eleven bits per element
	{
		BitArray<numberOfArrayElements, 11, false> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 2047);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(2047, bitArray.Get(i));
		}
	}

	//Five thirteen bits per element
	{
		BitArray<numberOfArrayElements, 13, false> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 8191);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(8191, bitArray.Get(i));
		}
	}
}

TEST_F(BitArray_static_test, Truncating_set_bits)
{
	constexpr unsigned numberOfArrayElements = 25;

	BitArray<numberOfArrayElements, 4, false> bitArray;

	//0b101010 which is 42 should be truncated to 0b1010 which is 10
	bitArray.Set(0, 42);

	//0b100111 should be truncated to 0b0111
	bitArray.Set(1, 0b100111);

	//0b101100 which is 42 should be truncated to 12
	bitArray.Set(2, 44);

	//16 which is 0b10000 should be truncated to 0
	bitArray.Set(3, 16);

	//Set the last value for test to the last element if array 31 should be truncated to 15
	bitArray.Set(24, 31);

	//Check the values
	EXPECT_EQ(10, bitArray.Get(0));
	EXPECT_EQ(7, bitArray.Get(1));
	EXPECT_EQ(12, bitArray.Get(2));
	EXPECT_EQ(0, bitArray.Get(3));
	EXPECT_EQ(15, bitArray.Get(24));
}