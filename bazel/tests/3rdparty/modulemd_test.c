/* Link/run smoke test for libmodulemd: parse a modulemd-defaults document. */
#include <modulemd.h>
#include <stdio.h>

static const char *yaml =
    "---\n"
    "document: modulemd-defaults\n"
    "version: 1\n"
    "data:\n"
    "  module: nodejs\n"
    "  stream: \"20\"\n"
    "...\n";

int main(void) {
    g_autoptr(GError) error = NULL;
    g_autoptr(ModulemdModuleIndex) index = modulemd_module_index_new();
    g_autoptr(GPtrArray) failures = NULL;
    if (!modulemd_module_index_update_from_string(index, yaml, TRUE, &failures, &error))
        return 1;
    ModulemdModule *module = modulemd_module_index_get_module(index, "nodejs");
    if (!module)
        return 2;
    ModulemdDefaults *defaults = modulemd_module_get_defaults(module);
    const char *stream = modulemd_defaults_v1_get_default_stream(MODULEMD_DEFAULTS_V1(defaults), NULL);
    printf("libmodulemd %s: nodejs default stream %s\n", modulemd_get_version(), stream);
    return g_strcmp0(stream, "20") == 0 ? 0 : 3;
}
