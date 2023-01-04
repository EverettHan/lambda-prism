#ifndef DSYSysCxxExceptionHelpers_H
#define DSYSysCxxExceptionHelpers_H

#include <functional>

namespace DSY
{

    template<typename T, typename Callable>
    inline bool Find_all_nested(Callable&& iFunc, const std::function<void(void)> & CThrow = []() { throw; }, int level = 0)
    {
        try {
            CThrow();  // To attempt to recognize the exception type
        }
        // we must attempt to catch a nested_exception FIRST, to avoid kind of type-slicing issues:
        //   when catched as a T, the exception is not seen as a nested_exception anymore, while it may be. Hence,
        //   depending on T, an attempt to invoke "rethrow_if_nested" may fail if dynamic_cast cannot be used (can_dynamic_cast?).
        catch (const std::nested_exception& e) {
            // IMPORTANT: "e" could also be a derived-type of T
            // Check it with a rethrow and not a dynamic_cast to avoid a bunch of pitfalls, such as:
            // T being a pointer-type, not compatible with dynamic_cast for e.g (solvable with templates though, at the cost of added complexity, cf. can_dynamic_cast<T>).
            try {
                throw;
            }
            catch (T& e2) {
                if (!iFunc(e2, level))
                    return false;   // Request to stop iteration
            }
            catch (...) {}  // Not a T
            
            if(e.nested_ptr())  // Required to avoid risk of std::terminate being called...
            {
                return Find_all_nested<T, Callable>(std::forward<Callable>(iFunc), [&e]() {
                    e.rethrow_nested();
                }, level + 1);
            }
        }
        catch (T& e) {
            // Last iteration
            return iFunc(e, level);
        }
        catch (...) {
            // Neither a T nor a nested exception, search is finished
        }
        return true;
    }   // Find_all_nested
    
}   // namespace DSY

#endif  // DSYSysCxxExceptionHelpers_H
