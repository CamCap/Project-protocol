# RAII

## SideCommunity
독학의 한계를 느끼던 도중에 찾은 Youtube의 프로그래밍 강의채널을 보고 있습니다. SideCommunity가 위에 올라간 글과 태그는 해당 강의를 정의한 내용입니다.

---------

Resource Acquisition Is Initialization의 약자

> **생성자와 파괴자가 자동으로 실행되는 기능을 이용하여 리소스를 자동으로 생성/파괴하는 패턴. 리소스 관리에 예외가 발생하는걸 방지하기 위함**

------

## boost의 socpe exit 매크로  
>socpe안에 socpe exit를 선언하면, 해당 socpe를 벗어나기 전에 해당 scope exit를 실행한다.  

    {
        BOOST_SCOPE_EXT()
        {
            //...
        }
        //..scope를 실행
        //scope를 벗어나기 전에 BOOST_SCOPE_EXT를 실행
    }
  
 -------  
   
## Dummy macro  

### **동기**
종종 나같은 프로그래머들은 디버깅시에, 브레이크포인트 이전에 의미가 없는 코드를 추가로 삽입하는 경우가 있다.  
int a = 0 같은 코드를 말이다. 그러나 이 더미(dummy)의 이름을 중복되지않게 선언해야한다. 이를 매크로로 해결할 수 있다.

------

### 토큰 연결 연산자

##이라는 전처리의 **토큰 연결 연산자**를 이용하여 Dummy를 어디서든 삽입할 수 있게한다.  

    #define STRING_CAT(a,b ) a ## b
    //는 다음과 같이 치환된다.
    ab

이를 다시 한 번 매크로로 덮어주면 우리가 원하는 Dummy 코드가 된다.  
    #define DUMMY int STRING_CAT(_dummy, 0) = 0;
    //다음과 같이 치환된다.
    int _dummy0 = 0;

토큰 연결 연산자를 매개변수 두개를 붙여준다. 이런걸 이렇게 쓰다니, 역시 프로그래머들은 대단해..

--------

### __LINE__매크로

> 문서파일의 줄 번호로 치환하는 매크로이다.

Dummy를 사용할 때, STRING_CAT의 b에 들어갈 변수는 매번 바뀌어야한다. 이를 돌려서 해결하는 방법이 __LINE__매크로이다.  
DUMMY를 문서의 10번째 줄에 사용했다면, STRING(_dummy, 10)으로 치환된다. 선언은 다음과 같다.

    #define DUMMY int STRING_CAT(_dummy, __LINE__) = 0;

하지만, 이대로는 컴파일 에러가 발생한다.
위의 코드는 다음과 같이 치환되기 떄문이다.

    int _dummy__LINE__ = 0;
    //이래서는 __LINE__을 매크로로 인식하지 못한다. _dummy__LINE__을 하나로 인식하기 때문.

그래서 토큰 연결 연산자를 손봐야한다. DUMMY를 20번째 줄에 사용했다고 가정하고 쓰겠다.

    #define _STRING_CAT(a,b) a ## b
    #define STRING_CAT(a,b) _STRING_CAT(a,b)
    #define DUMMY iny STRING_CAT(_dummy, __LINE__) = 0;
    //int STRING_CAT(_dummy, 20) = 0;
    //int _dummy_20 = 0;
    //로 치환된다.




## if의 특징

if의 ()에 변수선언이 가능하다는 것. 이건 몇 번 보긴했는데, 그때마다 불필요한 기능이라고 생각했었는데, 교수님이 잘 설명해주셨다. 딱히 특별한건 없어서 설명하지는 않겠습니다만, 궁금하시다면 링크를 보세요~


---------

[RAII (1)](https://www.youtube.com/watch?v=76Ka8JwSfIk)