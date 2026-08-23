#include <WString.h>
class TopicBuilder
{
    private:
        
    public:
        TopicBuilder(/* args */);
        ~TopicBuilder();
        static String Telemetry(const String& id);
        static String Status(const String& id);
        static String Command(const String& id);
        static String Ota(const String& id);
};