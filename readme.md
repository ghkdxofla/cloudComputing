# 클라우드 컴퓨팅 (전공수업)
---
### 180903
```
간단한 클라우드 컴퓨팅의 정의를 설명
쓴 만큼 내는 것으로 간단히 정의 가능
- 업그레이드 비용을 줄여줌
PaaS, IaaS 등...
```
### 180905
```
message passing, shared memory로 데이터 공유
- 분산처리는 message passing을 통해 이루어진다
synchronization에 쓰는 툴은?
- semaphore
synchronous VS asynchronous?
- 동기화를 하는지, 주고 답장 올 때 까지 wait 있는지 여부가 가장 큰 차이
concurrency, parallelizing
- 2 phase locking protocol
deadlock 발생조건은?
- mutual exclusion, hold and wait 등
분산처리의 특징
- no global clock(logical clock)
- 유비쿼터스
openness?
- 확장성이 얼마나 있는지, 새로운 자원 공유 서비스가 얼마나 추가될 수 있는지
security?
- confidentiality(권한 있는 사람만)
- integrity(변형 방지)
- availability(항상 사용 가능한지)
scalability?
- 비용 조절(O(N) or O(NlogN) 정도가 유지되어야 한다)
- 퍼포먼스 컨트롤(좀 더 좋은 자료구조를 사용하여 자원 관리)
- 로드밸런싱(효율적으로 자원 요청을 분배해서 처리)
failure handling
- 전체 시스템에 악영향을 줄 수 있음
- cold standard...?
- 감지(변조된 데이터 탐지)
- 마스킹(데이터 쌍으로 디스크에 기록하여 옳은 데이터 유지, 데이터 재전송)
- tolerating(실패 감내)
- 복구(체크포인트 사용)
```
### 180910
```
개인 사정으로...
```
### 180912
```
on-premise environment : 개인이나 기업의 로컬로 구축된 환경(미리)
```
### 180919
```
분산처리는 partial ordering만 된다
- total ordering을 하려면 order로 일어나기 전 과정까지 고려해야 한다
local의 state는 명확, 다른 process간의 happen, before는 어렵다
- global state가 필요함
global state?
- distributed garbage collection
consistent cut?
- cut 했을 때 global state 내에 보낸 process는 있는 경우
inconsistent cut?
- 서로 다른 process간 interaction에서 order는 interaction의 전 process 작업 -> interaction 작업 -> interaction의 후 process 작업 순으로만 확인 가능
- cut 했을 때 global state 내에 안쪽만 봤을 때 받았다는 process 만 있을 경우(orphan message)
```
### 181008
```
Hypervisor?
- Virtualization software를 부른다
Web쪽은 빼고 간다고 하심(Multitenant Technology 전 부분)
- 이후의 service technology 파트에서도 web쪽은 다 제외

Multitenant technology?
- 
```