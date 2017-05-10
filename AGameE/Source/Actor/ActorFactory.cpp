#include"ActorFactory.h"

using namespace std;

typedef ActorComponent* (*ActorComponentCreator)(void);
typedef std::map<string, ActorComponentCreator> ActorComponentCreatorMap;

//some actor typedefs to make code more beautiful
typedef shared_ptr<Actor> StrongActorPtr;
typedef shared_ptr<ActorComponent> StrongActorComponentPtr;