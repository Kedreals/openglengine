#include "debug.hpp"

std::ostream& operator <<(std::ostream& lhs, const glm::mat4& rhs)
{
  return lhs << "{"
	     << "[" << rhs[0][0] << ", " << rhs[0][1] << ", " << rhs[0][2] << ", " << rhs[0][3] << "]\n"
	     << "[" << rhs[1][0] << ", " << rhs[1][1] << ", " << rhs[1][2] << ", " << rhs[1][3] << "]\n"
	     << "[" << rhs[2][0] << ", " << rhs[2][1] << ", " << rhs[2][2] << ", " << rhs[2][3] << "]\n"
	     << "[" << rhs[3][0] << ", " << rhs[3][1] << ", " << rhs[3][2] << ", " << rhs[3][3] << "]}\n";
}
