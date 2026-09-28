#ifndef NEW_PARSER_H
#define NEW_PARSER_H

#include "file_loader.h"
#include "status.h"

Status setup_parser(void);
Status start_parser(FileString *file_string);

#endif
