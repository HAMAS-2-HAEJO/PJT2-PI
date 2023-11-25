# PJT2-PI
TC275 shieldbuddy를 활용하여 AURIX Development Studio내 PI 제어기 기반 ACC 시스템 개발 
 
## 프로젝트 배경

---

- ACC 기능의 일환으로 차간 거리에 따른 속도 제어를 구현하여 차량 간 안전거리 확보에 중점
- 거리 값에 따른 속도 제어는 PI 제어기로 구현하여 Closed-loop system에 대해 익힘

## 프로젝트 목적

- PID 원리에 대한 이해를 기반으로 거리와 속도에 대해 이중 PI 제어기를 통한 차간 거리 기반 속도 조절 시스템의 구축.
- Encoder 값을 활용하여 모터 속도를 계산하는 시스템 구축.
- Matlab Simulink를 기반으로 PI 제어기의 최적화된 계수를 도출하여 모터 속도 유지 안정화.

## 주요기능

---

- ToF센서를 사용하여 전방 차량과의 거리 측정
- 차간 목표거리 유지를 위해 PI제어기를 활용한 목표 속도 도출
- 도출된 목표 속도에 도달하고자, PI제어기를 활용하여 현재 속도 제어

## 프로젝트 개발환경

---

| S/W 개발환경 | 상세내용 |
| --- | --- |
| IDE | Aurix Development Studio, Matlab 및 Simulink  |
| 개발언어 | C, Matlab |
| 기타사항 |  |

| H/W 구성장비 | 상세내용 |
| --- | --- |
| 개발 보드 | - TC275 Shield Buddy |
| 추가 모듈 | - Arduino Motor Shield Rev3 |
| 사용 센서 | ToF센서 ( 레이저 센서 ), 엔코더 부착 DC 모터 |
| 기타사항 |  |

| 프로젝트 | 관리환경 |
| --- | --- |
| 형상관리 | Git |
| 의사소통관리 | Notion, 카카오톡 |
| 기타사항 |  |

## 프로젝트 결과

> PI 제어 시뮬레이션 구성도
> 

<img src="https://github.com/HAMAS-2-HAEJO/PJT2-PI/assets/87352996/7cbbc72d-5161-47fc-a17c-6aff52c9deea.png" width="700" height="300"/>   


   
> 하드웨어 구성도
> 

<img src="https://github.com/HAMAS-2-HAEJO/PJT2-PI/assets/87352996/17caf14d-33f7-4111-94bb-682409d500fc.png" width="500" height="280"/>   



> PI제어기 흐름도
> 

- 거리 오차에 따른 목표 속도   &    속도 오차에 따른 위치

<img src="https://github.com/HAMAS-2-HAEJO/PJT2-PI/assets/87352996/f61bed92-f63d-4e5e-b4f3-1a790f67b8d2.png" width="270" height="420"/>  
<img src="https://github.com/HAMAS-2-HAEJO/PJT2-PI/assets/87352996/8aacc695-afef-4138-9b55-bf7ace602686.png" width="280" height="400"/>  

   

> 예측 시뮬레이션 결과
> 
- 전방 챠량 속도 변화에 따른 속도 제어

<img src="https://github.com/HAMAS-2-HAEJO/PJT2-PI/assets/87352996/fd0956b3-aee4-40f1-abd4-ce02b668bbd8.png" width="500" height="280"/>  


- 기준 속도 60과의 차이값 그래프

<img src="https://github.com/HAMAS-2-HAEJO/PJT2-PI/assets/87352996/e2580fa2-bf5b-411d-8d11-2bedad40a0bd.png" width="500" height="280"/>  
