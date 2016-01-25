#if __cplusplus
#define public
#else
using System;
namespace Editor
{
#endif

	public enum StreamInstructionTypes
    {
		STREAM_INSTRUCTION_EOF = 0,
		STREAM_INSTRUCTION_CALL,
    };

#if __cplusplus
#undef public
#else
}
#endif
