#include <libsmartcols/libsmartcols.h>
#include <stdio.h>

int main(void) {
    struct libscols_table *tb = scols_new_table();
    if (!tb)
        return 1;
    scols_table_new_column(tb, "NAME", 0, 0);
    struct libscols_line *ln = scols_table_new_line(tb, NULL);
    scols_line_set_data(ln, 0, "dnf5");
    scols_table_enable_json(tb, 1);
    scols_print_table(tb);
    scols_unref_table(tb);
    return 0;
}
