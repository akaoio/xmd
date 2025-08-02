/**
 * @file ast_find_matching_endfor.h
 * @brief Find matching endfor directive for AST processor
 * @author XMD Team
 * @date 2025-07-29
 */

#ifndef AST_FIND_MATCHING_ENDFOR_H
#define AST_FIND_MATCHING_ENDFOR_H

/**
 * @brief Find matching endfor directive
 * @param input Input string starting after the for directive
 * @return Pointer to the endfor directive or NULL if not found
 */
const char* ast_find_matching_endfor(const char* input);

#endif /* AST_FIND_MATCHING_ENDFOR_H */
