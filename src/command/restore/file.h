/***********************************************************************************************************************************
Restore File
***********************************************************************************************************************************/
#ifndef COMMAND_RESTORE_FILE_H
#define COMMAND_RESTORE_FILE_H

#include "common/compress/helper.h"
#include "common/type/variant.h"

/***********************************************************************************************************************************
Restore file types
***********************************************************************************************************************************/
typedef enum
{
    restoreResultPreserve,
    restoreResultZero,
    restoreResultCopy,
} RestoreResult;

/***********************************************************************************************************************************
Functions
***********************************************************************************************************************************/
// Copy a file from the backup to the specified destination
typedef struct RestoreFile
{
    const String *name;                                             // File to restore
    const Buffer *checksum;                                         // Expected checksum
    uint64_t size;                                                  // Expected size
    time_t timeModified;                                            // Original modification time
    mode_t mode;                                                    // Original mode
    bool zero;                                                      // Should the file be zeroed?
    const String *user;                                             // Original user
    const String *group;                                            // Original group
    uint64_t offset;                                                // Offset into repo file where pg file is located
    const Variant *limit;                                           // Limit for read in the repo file
    const String *manifestFile;                                     // Manifest file
} RestoreFile;

typedef struct RestoreFileResult
{
    const String *manifestFile;                                     // Manifest file
    RestoreResult result;                                           // Restore result (e.g. preserve, copy)
} RestoreFileResult;

List *restoreFile(
    const String *repoFile, unsigned int repoIdx, CompressType repoFileCompressType, time_t copyTimeBegin, bool delta,
    bool deltaForce, const String *cipherPass, const List *fileList);

#endif
