# see https://gitlab.cern.ch/proteus/proteus/-/commit/8d906a45801c03832531e243f41f5f5a83177de0
IF (NOT SOURCE_FILES)
    MESSAGE(FATAL_ERROR "Variable SOURCE_FILES not defined")
    RETURN()
ENDIF ()

# Adding clang-format check and formatter if found
FIND_PROGRAM(CLANG_FORMAT "clang-format")
IF (CLANG_FORMAT)
    ADD_CUSTOM_TARGET(
            format
            COMMAND
            ${CLANG_FORMAT}
            -i
            -style=file
            ${SOURCE_FILES}
            COMMENT "Auto formatting of all source files"
    )

    ADD_CUSTOM_TARGET(
            check-format
            COMMAND
            ${CLANG_FORMAT}
            -style=file
            -output-replacements-xml
            ${SOURCE_FILES}
            # print output
            | tee ${CMAKE_BINARY_DIR}/check_format_file.txt | grep -c "replacement " |
            tr -d "[:cntrl:]" && echo " replacements necessary"
            # WARNING: fix to stop with error if there are problems
            COMMAND ! grep -c "replacement "
            ${CMAKE_BINARY_DIR}/check_format_file.txt > /dev/null
            COMMENT "Checking format compliance"
    )
ENDIF ()

# Adding clang-tidy check
FIND_PROGRAM(CLANG_TIDY "clang-tidy")
IF (CLANG_TIDY)
    ADD_CUSTOM_TARGET(
            lint
            COMMAND
            ${CLANG_TIDY}
            --format-style=file
            -p ${CMAKE_BINARY_DIR}
            ${SOURCE_FILES}
            COMMENT "Run clang-tidy checks"
    )
ENDIF ()
