#ifndef GHERKIN_AST_BUILDER_H_
#define GHERKIN_AST_BUILDER_H_

#include "builder.h"
#include "gherkin_document.h"
#include "id_generator.h"

#ifdef __cplusplus
extern "C" {
#endif

Builder* AstBuilder_new(IdGenerator* id_generator);

void AstBuilder_delete(Builder* builder);

const GherkinDocument* AstBuilder_get_result(Builder* builder, const char* uri);

#ifdef __cplusplus
}
#endif

#endif /* GHERKIN_AST_BUILDER_H_ */
