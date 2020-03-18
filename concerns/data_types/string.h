typedef struct string* string;

string string_new();
size_t string_length(string v);
void string_push(string v, char el);
void string_set(string v, unsigned index, char el);
char string_get(string v, unsigned index);
void string_delete(string v, unsigned index);
void string_delete_range(string v, unsigned start, unsigned end);
void string_insert_empty_range(string v, unsigned start, unsigned len);
void string_free(string v);

char *string_to_cstr(string v);
