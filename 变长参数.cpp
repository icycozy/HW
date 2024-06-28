void debugPrint() {
    std::cout<<std::endl;
    return;
}
template <typename T, typename... Tlist>
void debugPrint(T s, Tlist... rest) {
    std::cout<<s<<" ";
    debugPrint(rest...);
}