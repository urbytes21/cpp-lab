namespace external {
// 3. Inline const/constexpr in header file
inline const int kInlineConstVar{100};
constexpr int kConstexprVar{500};

namespace name {
extern int namespace_var;
}
}  // namespace external
