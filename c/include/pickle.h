#ifndef GHERKIN_PICKLE_H_
#define GHERKIN_PICKLE_H_

#include <wchar.h>

#include "item.h"
#include "pickle_ast_node_id.h"
#include "pickle_tag.h"
#include "pickle_step.h"
#include "id_generator.h"
#include "location.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Pickle {
    item_delete_function pickle_delete;
    wchar_t* uri;
    Location location;
    wchar_t* language;
    const PickleAstNodeIds* ast_node_ids;
    const PickleTags* tags;
    wchar_t* name;
    const wchar_t* id;
    const PickleSteps* steps;
} Pickle;

const Pickle* Pickle_new(IdGenerator* id_generator, const wchar_t* uri, Location location, const wchar_t* language, const PickleAstNodeIds* ast_node_ids, const PickleTags* tags, const wchar_t* name, const PickleSteps* steps);

void Pickle_delete(const Pickle* pickle);

#ifdef __cplusplus
}
#endif

#endif /* GHERKIN_PICKLE_H_ */
