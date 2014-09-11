#pragma once

#include <stddef.h>


/** Позволяет считать количество различных событий, произошедших в программе
  *  - для высокоуровневого профайлинга.
  */

#define APPLY_FOR_EVENTS(M) \
	M(Query, 							"Queries") \
	M(SelectQuery, 						"Select queries") \
	M(InsertQuery, 						"Insert queries") \
	M(FileOpen, 						"File opens") \
	M(Seek, 							"Seeks") \
	M(ReadBufferFromFileDescriptorRead, "ReadBufferFromFileDescriptor reads") \
	M(ReadCompressedBytes, 				"Read compressed bytes") \
	M(CompressedReadBufferBlocks, 		"Read decompressed blocks") \
	M(CompressedReadBufferBytes, 		"Read decompressed bytes") \
	M(UncompressedCacheHits, 			"Uncompressed cache hits") \
	M(UncompressedCacheMisses, 			"Uncompressed cache misses") \
	M(UncompressedCacheWeightLost,		"Uncompressed cache weight lost") \
	M(IOBufferAllocs, 					"IO buffers allocations") \
	M(IOBufferAllocBytes, 				"IO buffers allocated bytes") \
	M(ArenaAllocChunks, 				"Arena allocated chunks") \
	M(ArenaAllocBytes, 					"Arena allocated bytes") \
	M(FunctionExecute, 					"Function executes") \
	M(MarkCacheHits, 					"Mark cache hits") \
	M(MarkCacheMisses, 					"Mark cache misses") \
	\
	M(ReplicatedPartFetches, 			"Replicated part fetches") \
	M(ReplicatedPartFailedFetches,		"Replicated part fetches failed") \
	M(ObsoleteReplicatedParts,			"Replicated parts rendered obsolete by fetches") \
	M(ReplicatedPartMerges,				"Replicated part merges") \
	M(ReplicatedPartFetchesOfMerged,	"Replicated part merges replaced with fetches") \
	M(ReplicatedPartChecks,				"Replicated part checks") \
	M(ReplicatedPartChecksFailed,		"Replicated part checks failed") \
	\
	M(ZooKeeperInit,					"ZooKeeper session init") \
	M(ZooKeeperTransactions,			"ZooKeeper transaction (all types)") \
	M(ZooKeeperGetChildren,				"ZooKeeper get children") \
	M(ZooKeeperCreate,					"ZooKeeper create") \
	M(ZooKeeperRemove,					"ZooKeeper remove") \
	M(ZooKeeperExists,					"ZooKeeper exists") \
	M(ZooKeeperGet,						"ZooKeeper get") \
	M(ZooKeeperSet,						"ZooKeeper set") \
	M(ZooKeeperMulti,					"ZooKeeper multi") \
	M(ZooKeeperExceptions,				"ZooKeeper exceptions") \
	\
	M(END, "")

namespace ProfileEvents
{
	/// Виды событий.
	enum Event
	{
	#define M(NAME, DESCRIPTION) NAME,
		APPLY_FOR_EVENTS(M)
	#undef M
	};


	/// Получить текстовое описание события по его enum-у.
	inline const char * getDescription(Event event)
	{
		static const char * descriptions[] =
		{
		#define M(NAME, DESCRIPTION) DESCRIPTION,
			APPLY_FOR_EVENTS(M)
		#undef M
		};

		return descriptions[event];
	}


	/// Счётчики - сколько раз каждое из событий произошло.
	extern size_t counters[END];


	/// Увеличить счётчик события. Потокобезопасно.
	inline void increment(Event event, size_t amount = 1)
	{
		__sync_fetch_and_add(&counters[event], amount);
	}
}


#undef APPLY_FOR_EVENTS
