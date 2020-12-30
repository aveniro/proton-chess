/**
 * @file test.c
 * @author Nathan Seymour
 * @brief Entrypoint for protonchess tests.
 */

#include "scpunitc.h"
#include "extensions.h"

DEFINE_SUITE(ProtonChessMain);
DEFINE_SUITE(PCStrings);

#ifdef FEN_EXTENSIONS
DEFINE_SUITE(FENExtensions);
#endif

#ifdef IMPORT_EXPORT_EXTENSIONS
#endif

int main()
{
    RUN_SUITE(ProtonChessMain);
    RUN_SUITE(PCStrings);

#ifdef FEN_EXTENSIONS
    RUN_SUITE(FENExtensions);
#endif

    return _has_error;
}