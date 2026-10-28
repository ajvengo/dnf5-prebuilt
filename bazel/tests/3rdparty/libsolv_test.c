/* Link/run smoke test for libsolv + libsolvext: solve a tiny testcase. */
#include <solv/pool.h>
#include <solv/poolarch.h>
#include <solv/repo.h>
#include <solv/repo_solv.h>
#include <solv/selection.h>
#include <solv/solver.h>
#include <solv/solvversion.h>
#include <solv/testcase.h>
#include <solv/transaction.h>
#include <stdio.h>

int main(void) {
    Pool *pool = pool_create();
    pool_setarch(pool, "x86_64");
    Repo *repo = repo_create(pool, "available");
    Solvable *s = pool_id2solvable(pool, repo_add_solvable(repo));
    s->name = pool_str2id(pool, "dnf5", 1);
    s->evr = pool_str2id(pool, "5.4.6.0-1", 1);
    s->arch = pool_str2id(pool, "x86_64", 1);
    s->provides = repo_addid_dep(repo, s->provides, pool_rel2id(pool, s->name, s->evr, REL_EQ, 1), 0);
    repo_internalize(repo);
    pool_createwhatprovides(pool);

    Queue job;
    queue_init(&job);
    selection_make(pool, &job, "dnf5", SELECTION_NAME);
    for (int i = 0; i < job.count; i += 2)
        job.elements[i] |= SOLVER_INSTALL;
    Solver *solv = solver_create(pool);
    if (solver_solve(solv, &job) != 0)
        return 1;
    Transaction *trans = solver_create_transaction(solv);
    if (trans->steps.count != 1)
        return 2;
    printf("libsolv %s: installs %s\n", solv_version, pool_solvid2str(pool, trans->steps.elements[0]));
    transaction_free(trans);
    solver_free(solv);
    queue_free(&job);
    pool_free(pool);
    return 0;
}
