--
-- PostgreSQL database dump
--

-- Dumped from database version 17.2
-- Dumped by pg_dump version 17.2

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: act; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.act (
    id integer NOT NULL,
    article text NOT NULL,
    name text NOT NULL,
    count integer NOT NULL
);


--
-- Name: act_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.act_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: act_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.act_id_seq OWNED BY public.act.id;


--
-- Name: user; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public."user" (
    id integer NOT NULL,
    login text NOT NULL,
    password text NOT NULL
);


--
-- Name: administrator; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.administrator (
    first_name text NOT NULL,
    last_name text NOT NULL,
    email text NOT NULL
)
INHERITS (public."user");


--
-- Name: administrator_backup; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.administrator_backup (
    id integer,
    firstname text,
    lastname text,
    email text
);


--
-- Name: manager; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.manager (
    first_name text NOT NULL,
    last_name text NOT NULL,
    email text NOT NULL
)
INHERITS (public."user");


--
-- Name: manager_backup; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.manager_backup (
    id integer,
    firstname text,
    lastname text,
    email text
);


--
-- Name: medkit; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.medkit (
    id integer NOT NULL,
    number text NOT NULL,
    name text NOT NULL,
    status text NOT NULL,
    storagelocation text NOT NULL,
    storage_id integer,
    manager_id integer,
    transferdate date,
    daysinstorage integer,
    comments text,
    department text,
    tab_id integer
);


--
-- Name: medkit_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.medkit_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: medkit_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.medkit_id_seq OWNED BY public.medkit.id;


--
-- Name: medkitcontent; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.medkitcontent (
    id integer NOT NULL,
    medkit_id integer NOT NULL,
    act_id integer,
    photo_id integer
);


--
-- Name: medkitcontent_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.medkitcontent_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: medkitcontent_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.medkitcontent_id_seq OWNED BY public.medkitcontent.id;


--
-- Name: photo; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.photo (
    id integer NOT NULL,
    name text NOT NULL,
    path text NOT NULL
);


--
-- Name: photo_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.photo_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: photo_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.photo_id_seq OWNED BY public.photo.id;


--
-- Name: request; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.request (
    id integer NOT NULL,
    medkitnumber integer,
    orderstatus text NOT NULL,
    manager_id integer
);


--
-- Name: request_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.request_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: request_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.request_id_seq OWNED BY public.request.id;


--
-- Name: storage; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.storage (
    id integer NOT NULL,
    name text NOT NULL,
    address text NOT NULL
);


--
-- Name: storage_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.storage_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: storage_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.storage_id_seq OWNED BY public.storage.id;


--
-- Name: tab; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.tab (
    id integer NOT NULL,
    name text NOT NULL
);


--
-- Name: tab_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.tab_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: tab_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.tab_id_seq OWNED BY public.tab.id;


--
-- Name: transferlog; Type: TABLE; Schema: public; Owner: -
--

CREATE TABLE public.transferlog (
    id integer NOT NULL,
    date date NOT NULL,
    fromlocation text NOT NULL,
    tolocation text NOT NULL,
    comment text,
    medkit_id integer
);


--
-- Name: transferlog_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.transferlog_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: transferlog_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.transferlog_id_seq OWNED BY public.transferlog.id;


--
-- Name: user_id_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE public.user_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


--
-- Name: user_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE public.user_id_seq OWNED BY public."user".id;


--
-- Name: act id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.act ALTER COLUMN id SET DEFAULT nextval('public.act_id_seq'::regclass);


--
-- Name: administrator id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.administrator ALTER COLUMN id SET DEFAULT nextval('public.user_id_seq'::regclass);


--
-- Name: manager id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.manager ALTER COLUMN id SET DEFAULT nextval('public.user_id_seq'::regclass);


--
-- Name: medkit id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkit ALTER COLUMN id SET DEFAULT nextval('public.medkit_id_seq'::regclass);


--
-- Name: medkitcontent id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkitcontent ALTER COLUMN id SET DEFAULT nextval('public.medkitcontent_id_seq'::regclass);


--
-- Name: photo id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.photo ALTER COLUMN id SET DEFAULT nextval('public.photo_id_seq'::regclass);


--
-- Name: request id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.request ALTER COLUMN id SET DEFAULT nextval('public.request_id_seq'::regclass);


--
-- Name: storage id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.storage ALTER COLUMN id SET DEFAULT nextval('public.storage_id_seq'::regclass);


--
-- Name: tab id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.tab ALTER COLUMN id SET DEFAULT nextval('public.tab_id_seq'::regclass);


--
-- Name: transferlog id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.transferlog ALTER COLUMN id SET DEFAULT nextval('public.transferlog_id_seq'::regclass);


--
-- Name: user id; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE ONLY public."user" ALTER COLUMN id SET DEFAULT nextval('public.user_id_seq'::regclass);


--
-- Name: act act_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.act
    ADD CONSTRAINT act_pkey PRIMARY KEY (id);


--
-- Name: administrator administrator_email_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.administrator
    ADD CONSTRAINT administrator_email_key UNIQUE (email);


--
-- Name: manager manager_email_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.manager
    ADD CONSTRAINT manager_email_key UNIQUE (email);


--
-- Name: medkit medkit_number_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkit
    ADD CONSTRAINT medkit_number_key UNIQUE (number);


--
-- Name: medkit medkit_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkit
    ADD CONSTRAINT medkit_pkey PRIMARY KEY (id);


--
-- Name: medkitcontent medkitcontent_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkitcontent
    ADD CONSTRAINT medkitcontent_pkey PRIMARY KEY (id);


--
-- Name: photo photo_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.photo
    ADD CONSTRAINT photo_pkey PRIMARY KEY (id);


--
-- Name: request request_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.request
    ADD CONSTRAINT request_pkey PRIMARY KEY (id);


--
-- Name: storage storage_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.storage
    ADD CONSTRAINT storage_pkey PRIMARY KEY (id);


--
-- Name: tab tab_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.tab
    ADD CONSTRAINT tab_pkey PRIMARY KEY (id);


--
-- Name: transferlog transferlog_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.transferlog
    ADD CONSTRAINT transferlog_pkey PRIMARY KEY (id);


--
-- Name: user user_login_key; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public."user"
    ADD CONSTRAINT user_login_key UNIQUE (login);


--
-- Name: user user_pkey; Type: CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public."user"
    ADD CONSTRAINT user_pkey PRIMARY KEY (id);


--
-- Name: medkit medkit_storage_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkit
    ADD CONSTRAINT medkit_storage_id_fkey FOREIGN KEY (storage_id) REFERENCES public.storage(id) ON DELETE SET NULL;


--
-- Name: medkit medkit_tab_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkit
    ADD CONSTRAINT medkit_tab_id_fkey FOREIGN KEY (tab_id) REFERENCES public.tab(id) ON DELETE SET NULL;


--
-- Name: medkitcontent medkitcontent_act_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkitcontent
    ADD CONSTRAINT medkitcontent_act_id_fkey FOREIGN KEY (act_id) REFERENCES public.act(id) ON DELETE CASCADE;


--
-- Name: medkitcontent medkitcontent_medkit_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkitcontent
    ADD CONSTRAINT medkitcontent_medkit_id_fkey FOREIGN KEY (medkit_id) REFERENCES public.medkit(id) ON DELETE CASCADE;


--
-- Name: medkitcontent medkitcontent_photo_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.medkitcontent
    ADD CONSTRAINT medkitcontent_photo_id_fkey FOREIGN KEY (photo_id) REFERENCES public.photo(id) ON DELETE CASCADE;


--
-- Name: request request_medkitnumber_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.request
    ADD CONSTRAINT request_medkitnumber_fkey FOREIGN KEY (medkitnumber) REFERENCES public.medkit(id) ON DELETE CASCADE;


--
-- Name: transferlog transferlog_medkit_id_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY public.transferlog
    ADD CONSTRAINT transferlog_medkit_id_fkey FOREIGN KEY (medkit_id) REFERENCES public.medkit(id) ON DELETE CASCADE;


--
-- PostgreSQL database dump complete
--

