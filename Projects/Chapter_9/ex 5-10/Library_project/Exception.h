#include <string>
namespace Library_f::Exception
{
    class Exception
    {
    public:
        std::string what() { return what_p; }
        Exception();
        Exception(std::string what);

    private:
        std::string what_p;
    };
} // namespace Library_f::Exception