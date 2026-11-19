#include "step.h"
#include "data_table.h"
#include "doc_string.h"
#include "string_utilities.h"
#include <stdlib.h>

static void delete_step_content(const Step* step);

const Step* Step_new(Location location, IdGenerator* id_generator, const wchar_t* keyword, const KeywordType keyword_type, const wchar_t* text, const DataTable* data_table, const DocString* doc_string) {
    Step* step = (Step*)malloc(sizeof(Step));
    step->step_delete = (item_delete_function)Step_delete;
    step->type = Gherkin_Step;
    step->location.line = location.line;
    step->location.column = location.column;
    step->id = id_generator->new_id(id_generator);
    if (keyword) {
        step->keyword = StringUtilities_copy_string(keyword);
    }
    step->keyword_type = keyword_type;
    if (text) {
        step->text = StringUtilities_copy_string(text);
    }
    step->data_table = data_table;
    step->doc_string = doc_string;
    return step;
}

void Step_delete(const Step* step) {
    if (!step) {
        return;
    }
    delete_step_content(step);
    free((void*)step);
}

void Step_transfer(Step* to_step, Step* from_step) {
    to_step->type = from_step->type;
    to_step->location.line = from_step->location.line;
    to_step->location.column = from_step->location.column;
    to_step->id = from_step->id;
    from_step->id = 0;
    to_step->keyword = from_step->keyword;
    from_step->keyword = 0;
    to_step->keyword_type = from_step->keyword_type;
    to_step->text = from_step->text;
    from_step->text = 0;
    to_step->data_table = from_step->data_table;
    from_step->data_table = 0;
    to_step->doc_string = from_step->doc_string;
    from_step->doc_string = 0;
    Step_delete(from_step);
}

void Steps_delete(const Steps* steps) {
    if (!steps) {
        return;
    }
    if (steps->step_count > 0) {
        int i;
        for (i = 0; i < steps->step_count; ++i) {
            delete_step_content(steps->steps + i);
        }
        free((void*)steps->steps);
    }
    free((void*)steps);
}

static void delete_step_content(const Step* step) {
    if (step->keyword) {
        free((void*)step->keyword);
    }
    if (step->id) {
        free((void*)step->id);
    }
    if (step->text) {
        free((void*)step->text);
    }
    if (step->data_table) {
        DataTable_delete((DataTable*)step->data_table);
    }
    if (step->doc_string) {
        DocString_delete((DocString*)step->doc_string);
    }
}
