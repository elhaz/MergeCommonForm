#include "pch.h"
#include "framework.h"
#include <omp.h>
#include <string>

namespace merge {
	class MergeCommonForm {
	public:
		MergeCommonForm(char* recipe, char* src, char* dest);
		~MergeCommonForm();
	protected:
		void _ReadRecipe();
		void _SaveCommonForm();
	};
}
void fnMergeCommonForm()
{
}
