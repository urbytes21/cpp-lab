namespace External {
// 3. Inline const/constexpr in header file
inline const int INLINE_CONST_VAR{100};
constexpr int CONSTEXPR_VAR{500};

namespace Name {
extern int namespaceVar;
}
}  // namespace External
