# DocForge

Document Parsing & OCR Pipeline Engine in C++

---

## Overview

DocForge is a modular document processing engine built in modern C++.

The project focuses on extracting, structuring, and transforming data from multiple document formats such as PDF, DOCX, and Images into a unified internal pipeline for downstream AI and retrieval systems.

The engine was designed with scalability and extensibility in mind:

* Parser-oriented architecture
* OCR pipeline abstraction
* Chunk-based document processing
* Section detection
* Export system
* Multi-format support

---

# Features

## Document Parsing

Currently supported:

* PDF
* DOCX
* PNG
* JPG / JPEG

Each format is processed through its own parser implementation using a shared parser interface.

---

## OCR Pipeline

Integrated OCR processing using Tesseract OCR.

Capabilities:

* Image-based text extraction
* OCRBlock generation
* OCR utility abstraction
* OCR filtering system
* Shared OCR pipeline across parsers

---

## PDF Processing

Implemented using PDFium.

Current pipeline:

* PDF loading
* Page parsing
* Text extraction
* Image extraction
* Page rendering
* OCR processing for image regions

---

## Block-Based Architecture

Documents are internally represented using block structures.

Implemented block types:

* TextBlock
* ImageBlock
* OCRBlock

This allows flexible processing for:

* chunk generation
* section detection
* AI preprocessing
* retrieval systems

---

## Chunk System

Implemented fixed-size chunk generation system.

Chunk metadata includes:

* ChunkId
* StartPage
* EndPage
* CharacterCount
* TokenCount
* SectionName

Designed for:

* RAG pipelines
* vector database ingestion
* semantic retrieval systems

---

## Exporters

Current exporters:

* JSON Exporter
* TXT Exporter

Export pipeline is format-independent and registry-based.

---

# Architecture

```text
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
    ├── Blocks
    ├── OCRBlocks
    └── ImageBlocks
    ↓
Chunk Builder
    ↓
Section Detector
    ↓
Exporter
```

---

# OCR Pipeline

```text
ImageBlock
    ↓
OCRFilter
    ↓
OCRUtility
    ↓
OCRBlockBuilder
    ↓
OCRBlock
```

---

# Current Development Focus

* OCR filtering heuristics
* Block ordering system
* PDF image region extraction
* DOCX embedded image OCR
* Post-processing pipeline
* Semantic chunking
* Metadata enrichment
* Vector database integration

---

# Tech Stack

* C++17
* PDFium
* Tesseract OCR
* stb_image_write

---

# Design Goals

* Modular architecture
* Low coupling
* Extensible parser system
* AI-ready document pipeline
* High-performance preprocessing
* Cross-format document normalization

---

# Status

Actively in development.
