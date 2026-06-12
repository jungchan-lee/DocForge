# DocForge

### C++ 기반 문서 파싱 · OCR · Chunk 처리 엔진

---

## 프로젝트 개요 (Overview)

**DocForge**는 다양한 문서 파일로부터 데이터를 추출하고, 구조화된 형태로 변환하여 AI 시스템에서 바로 활용할 수 있도록 설계된 **Native C++ 기반 문서 처리 엔진**입니다.

PDF, DOCX, 이미지 파일을 분석하여 텍스트와 이미지 데이터를 추출하고, OCR 처리를 수행한 뒤 내부 문서 구조로 정규화하여 최종적으로 Chunk 단위 JSON 데이터로 변환합니다.

본 프로젝트는 확장 가능한 구조와 높은 성능의 문서 전처리 파이프라인 구축을 목표로 개발되었습니다.

핵심 목표

* 다양한 문서 포맷 지원
* OCR 기반 이미지 텍스트 추출
* 통합 문서 구조 생성
* AI 입력용 Chunk 데이터 생성
* JSON 기반 구조화 데이터 Export

---

## 지원 포맷 (Supported Formats)

현재 지원하는 문서 형식

* PDF
* DOCX
* PNG
* JPG / JPEG

각 문서 포맷은 공통 인터페이스 기반의 독립적인 Parser 구조로 설계되었습니다.

구현된 Parser

* PDFParser
* DOCXParser
* ImageParser

---

## 주요 기능 (Core Features)

### PDF 처리 (PDF Processing)

PDF 내부 Object 구조를 직접 순회하며 데이터를 추출합니다.

구현 기능

* PDF 문서 로드
* 페이지 단위 파싱
* Text Object 추출
* Image Object 추출
* Bitmap 변환
* 이미지 영역 OCR 처리

사용 라이브러리

* PDFium

---

### DOCX 처리 (DOCX Processing)

DOCX 압축 구조와 XML 구조를 직접 분석하여 데이터를 추출합니다.

구현 기능

* DOCX 압축 파일 해제
* document.xml 직접 파싱
* 텍스트 노드 추출
* 내부 Embedded Image 추출
* 이미지 OCR 처리

사용 라이브러리

* miniz
* pugixml

---

### OCR 처리 파이프라인 (OCR Pipeline)

문서 내부 이미지 영역에서 텍스트를 추출하는 OCR 시스템입니다.

구현 기능

* 이미지 텍스트 추출
* OCRBlock 생성
* OCR Utility 계층 분리
* OCR Filter 처리
* Parser 공통 OCR Pipeline 구축

처리 흐름

Image → OCR → OCRBlock 생성

사용 라이브러리

* Tesseract OCR
* Leptonica

---

### Block 기반 문서 구조 (Block-Based Architecture)

모든 문서는 내부적으로 Block 구조로 통합 관리됩니다.

구현된 Block 타입

* TextBlock
* ImageBlock
* OCRBlock

장점

* 문서 구조 표준화
* 포맷 독립적 처리 가능
* 후처리 Pipeline 연결 용이

---

### Chunk 생성 시스템 (Chunk Processing)

추출된 문서를 AI 시스템에서 활용할 수 있도록 Chunk 단위 데이터로 변환합니다.

생성되는 메타데이터

* ChunkId
* StartPage
* EndPage
* CharacterCount
* TokenCount
* SectionName

활용 분야

* RAG Pipeline
* Vector Database
* Semantic Search
* LLM 입력 데이터 생성

---

### Export 시스템 (Export System)

가공된 문서 데이터를 외부 시스템에서 활용할 수 있도록 Export 기능을 제공합니다.

현재 지원

* JSON Exporter
* TXT Exporter

Export 구조는 Registry 기반으로 설계되어 확장 가능합니다.

---

## 전체 구조 (Architecture)

Input File

↓

FileTypeResolver

↓

ParserRegistry

↓

Document Parser

├── PDFParser
├── DOCXParser
└── ImageParser

↓

Document Structure

├── Pages
├── TextBlocks
├── ImageBlocks
└── OCRBlocks

↓

Chunk Builder

↓

JSON Serialization

↓

Exporter

---

## OCR 처리 구조 (OCR Pipeline)

ImageBlock

↓

OCRFilter

↓

OCRUtility

↓

OCRBlockBuilder

↓

OCRBlock

---

## 기술 스택 (Tech Stack)

### Language

* C++

### Document Processing Libraries

* PDFium
* Tesseract OCR
* Leptonica
* miniz
* pugixml

### Processing

* OCR Pipeline
* JSON Serialization
* Chunk Processing
* Document Structure Normalization

---

## 설계 원칙 (Design Principles)

* 모듈형 구조 설계
* Parser 기반 구조
* 낮은 결합도 (Low Coupling)
* 다양한 문서 포맷 지원
* 확장 가능한 Export 구조
* AI 친화적 데이터 파이프라인 설계

---

## 현재 구현 상태 (Current Status)

구현 완료

* PDF Parser
* DOCX Parser
* Image Parser
* OCR Pipeline
* Block 기반 문서 구조
* Chunk Generation
* JSON Exporter
* TXT Exporter

개선 예정

* Semantic Chunking 고도화
* Metadata Enrichment
* OCR 정확도 향상
* 성능 최적화
* 추가 문서 포맷 지원

---

## 향후 계획 (Future Goals)

추가 개발 예정 기능

* DOC 지원
* PPTX 지원
* XLSX 지원
* 표(Table) 추출 기능
* 문서 레이아웃 분석
* Vector DB 연동
* Embedding Pipeline 구축

---
