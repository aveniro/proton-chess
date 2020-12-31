/**
 * @file test.c
 * @author Nathan Seymour
 * @brief Entrypoint for protonchess tests.
 */

#include "scpunitc.h"
#include "extensions.h"

DEFINE_SUITE(ProtonChessMain);
DEFINE_SUITE(Evaluation);
DEFINE_SUITE(Movement);
DEFINE_SUITE(PCStrings);
DEFINE_SUITE(PCMath);

#ifdef FEN_EXTENSIONS
DEFINE_SUITE(FENExtensions);
#endif

#ifdef IMPORT_EXPORT_EXTENSIONS
#endif

int main()
{
    RUN_SUITE(ProtonChessMain);
    RUN_SUITE(Evaluation);
    RUN_SUITE(Movement);
    RUN_SUITE(PCStrings);
    RUN_SUITE(PCMath);

#ifdef FEN_EXTENSIONS
    RUN_SUITE(FENExtensions);
#endif

    return _has_error;
}