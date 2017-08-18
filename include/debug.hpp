#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#include <iostream>
#include <glm/glm.hpp>

std::ostream& operator <<(std::ostream& lhs, const glm::mat4& rhs);

#endif //_DEBUG_HPP_
