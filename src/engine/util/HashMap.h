// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_UTIL_HASHMAP_H
#define ENGINE_UTIL_HASHMAP_H

#include <xxhash.h>
#include "engine/util/Array.h"

namespace engine {
namespace util {

	//TODO: Remove from hashmap not implemented
	//TODO: dynamic resizing of the hashmap

	template <typename T>
	class Bucket
	{
	private:
		typedef Bucket<T> BucketType;

		util::Array<String> keys;
		util::Array<T> values;

	public:
		const util::Array<String> &getKeys() const { return keys; };
		const util::Array<T> &getValues() const { return values; };

		void insertValue(const String &key, T value)
		{
			keys.push(key);
			values.push(value);
		}

		void removeByIndex(const unsigned &index)
		{
			assert(keys.getSize() <= index - 1);
			assert(values.getSize() <= index - 1);
			assert(keys.getSize() == values.getSize());

			keys.remove(index);
			values.remove(index);
		}
	};

	template <typename T, const unsigned bucketCount = 128> //TODO: rename the bucketCount casing to something sensible
	class HashMap
	{
	private:
		static const int HASHMAP_SEED = 666;

		unsigned itemCount;

		Bucket<T> *buckets;

	public:
		typedef HashMap<T, bucketCount> HashMapType;

		class Iterator
		{
		private:
			HashMapType *hashMap;
			unsigned currentBucket;
			unsigned slotInBucket;

			bool end;

			void destroy()
			{
				hashMap->buckets[currentBucket]->removeByIndex(slotInBucket);
				end = true;  //invalidate the current iterator
			}

		public:
			Iterator(HashMapType *hashMap, unsigned bucketId, unsigned slotInBucket)
				: hashMap(hashMap)
				, currentBucket(bucketId)
				, slotInBucket(slotInBucket)
				, end(false)
			{ }

			const String &getKey() const
			{
				const util::Array<String> &keys = hashMap->buckets[currentBucket].getKeys();
				return keys[slotInBucket];
			}

			const T &getValue()
			{
				return hashMap->buckets[currentBucket].getValues()[slotInBucket];
			}

			void operator ++ ()
			{
				// does the current bucket have one more element?
				if ((slotInBucket + 1) < hashMap->buckets[currentBucket].getKeys().getSize())
				{
					++slotInBucket; //extra element found, move iterator to it
					return;
				}

				// Find the next bucket and assign to the first element
				for (unsigned i = currentBucket + 1; i < hashMap->getBucketCount(); ++i)
				{
					if (hashMap->buckets[i].getKeys().getSize() > 0)
					{
						currentBucket = i;
						slotInBucket = 0;
						return;
					}
				}

				end = true; //Could not find anything!
			}


			bool isAtEnd() const { return end; }

			friend class HashMap;
		};

		friend class Iterator;

		HashMap()
			: itemCount(0)
		{
			buckets = new Bucket<T>[bucketCount]();
		}

		~HashMap()
		{
			delete [] (buckets);
		}

		// Return iterator to the first element of the map
		Iterator begin()
		{
			for (unsigned i = 0; i < bucketCount; ++i)
			{
				if (buckets[i].getKeys().getSize() > 0)
					return Iterator(this, i, 0); // Return iterator to first element in the first bucket with elements in it.
			}

			// failed to find iterator!
			assert(true);
			//TODO: add iterator to end() or something!
			return Iterator(this, 0, 0);//QQQ
		}

		int insert(const char *key, T value)
		{
			int k = XXH32(key, strlen(key), HASHMAP_SEED);

			++itemCount;

			buckets[k % bucketCount].insertValue(key, value);

			return (k % bucketCount);
		}

		bool find(const String &key, T &value)
		{
			int k = XXH32(key.data(), key.length(), HASHMAP_SEED);

			const util::Array<T> &values = buckets[k % bucketCount].getValues();
			const util::Array<String> &keys = buckets[k % bucketCount].getKeys();

			if (values.getSize() == 1)
			{
				value = values[0];
				return true;
			}

			for (unsigned i = 0; i < keys.getSize(); ++i)
			{
				if (keys[i] == key)
				{
					value = values[i];
					return true;
				}
			}

			return false;
		}

		void remove(const String &key)
		{
			int k = XXH32(key.data(), key.length(), HASHMAP_SEED);

			const util::Array<T> &values = buckets[k % bucketCount].getValues();
			const util::Array<String> &keys = buckets[k % bucketCount].getKeys();

			for (unsigned i = 0; i < keys.getSize(); ++i)
			{
				if (keys[i] == key)
				{
					buckets[k % bucketCount].removeByIndex(i);
					return;
				}
			}
		}

		void remove(const Iterator &it)
		{
			it.destroy();
		}

		const unsigned &getSize() const { return itemCount; }
		const unsigned getBucketCount() const { return bucketCount; }

		void clear()
		{
			delete [] (buckets);
			buckets = new Bucket<T>[bucketCount]();

			itemCount = 0;
		}
	};

}
}

#endif
