# mock

links: 
- https://cstack.github.io/db_tutorial/

## Current Issues

### 🚨 High Priority
1. **Fix misleading constants** - Replace `CURRENT_COMMAND = 1` with `#define` or proper boolean
2. **Fix inconsistent memory management** - Pick a pattern for freeing and stick to it
3. **Fix buffer overflow potential** - Change newline stripping from `>= 1` to `> 0`
4. **Add error handling** for `malloc/calloc` failures

### 🔧 Medium Priority
5. **Rename function** - `parse_repl_input()` → `read_user_input()` for clarity
6. **Extract helper function** - `strcat() + free()` pattern repeated
7. **Replace magic numbers** - `BUFFER_SIZE - 1` → named constant `MAX_COMMAND_LENGTH`

### 📝 Low Priority
8. **Fix inconsistent formatting** - standardize `if (condition)` vs `if(condition)`
9. **Add complete documentation** for all functions