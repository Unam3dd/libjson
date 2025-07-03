#include "libjson.h"

const char	*json_get_type_str(const json_type_t type)
{
	static const json_type_str_t j[] = {
		{ "JSON_NULL",   JSON_NULL    },
		{ "JSON_BOOL",   JSON_BOOL    },
		{ "JSON_OBJECT", JSON_OBJECT  },
		{ "JSON_ARRAY",  JSON_ARRAY   },
		{ "JSON_STRING", JSON_STRING  },
		{ "JSON_NUMBER", JSON_NUMBER  }
	};

	if (type < 0 || type >= sizeof(j)/sizeof(json_type_str_t))
		return (NULL);

	return ((type < 0 
				|| type >= sizeof(j)/sizeof(json_type_str_t)) 
			? NULL 
			: j[type].str);
}
