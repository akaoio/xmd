/**
 * @file process_html_tag.h
 * @brief Header for HTML tag processing function
 * @author XMD Development Team
 * @date 2025-08-04
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Header for extracted process_html_tag function
 */

#ifndef PROCESS_HTML_TAG_H
#define PROCESS_HTML_TAG_H

#include <stddef.h>

/**
 * @brief Process HTML tag using whitelist approach
 * @param tag_content The HTML tag content to process
 * @param output Output buffer to write sanitized content
 * @param output_pos Current position in output buffer
 * @param max_output_size Maximum size of output buffer
 * @return New position in output buffer after processing
 */
size_t process_html_tag(const char* tag_content, char* output, 
                       size_t output_pos, size_t max_output_size);

#endif // PROCESS_HTML_TAG_H