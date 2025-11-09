SELECT pg_catalog.set_config('search_path', '', false);

CREATE TABLE public.act (
    id integer NOT NULL,
    article text NOT NULL,
    name text NOT NULL,
    count integer NOT NULL
);

CREATE SEQUENCE public.act_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.act_id_seq OWNED BY public.act.id;

CREATE TABLE public."user" (
    id integer NOT NULL,
    login text NOT NULL,
    password text NOT NULL
);

CREATE TABLE public.administrator (
    first_name text NOT NULL,
    last_name text NOT NULL,
    email text NOT NULL
)
INHERITS (public."user");

CREATE TABLE public.administrator_backup (
    id integer,
    firstname text,
    lastname text,
    email text
);

CREATE TABLE public.manager (
    first_name text NOT NULL,
    last_name text NOT NULL,
    email text NOT NULL
)
INHERITS (public."user");

CREATE TABLE public.manager_backup (
    id integer,
    firstname text,
    lastname text,
    email text
);

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

CREATE SEQUENCE public.medkit_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.medkit_id_seq OWNED BY public.medkit.id;

CREATE TABLE public.medkitcontent (
    id integer NOT NULL,
    medkit_id integer NOT NULL,
    act_id integer,
    photo_id integer
);

CREATE SEQUENCE public.medkitcontent_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.medkitcontent_id_seq OWNED BY public.medkitcontent.id;

CREATE TABLE public.photo (
    id integer NOT NULL,
    name text NOT NULL,
    path text NOT NULL
);

CREATE SEQUENCE public.photo_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.photo_id_seq OWNED BY public.photo.id;

CREATE TABLE public.request (
    id integer NOT NULL,
    medkitnumber integer,
    orderstatus text NOT NULL,
    manager_id integer
);

CREATE SEQUENCE public.request_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.request_id_seq OWNED BY public.request.id;

CREATE TABLE public.storage (
    id integer NOT NULL,
    name text NOT NULL,
    address text NOT NULL
);

CREATE SEQUENCE public.storage_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.storage_id_seq OWNED BY public.storage.id;

CREATE TABLE public.tab (
    id integer NOT NULL,
    name text NOT NULL
);

CREATE SEQUENCE public.tab_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.tab_id_seq OWNED BY public.tab.id;

CREATE TABLE public.transferlog (
    id integer NOT NULL,
    date date NOT NULL,
    fromlocation text NOT NULL,
    tolocation text NOT NULL,
    comment text,
    medkit_id integer
);

CREATE SEQUENCE public.transferlog_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.transferlog_id_seq OWNED BY public.transferlog.id;

CREATE SEQUENCE public.user_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

ALTER SEQUENCE public.user_id_seq OWNED BY public."user".id;

ALTER TABLE ONLY public.act ALTER COLUMN id SET DEFAULT nextval('public.act_id_seq');

ALTER TABLE ONLY public.administrator ALTER COLUMN id SET DEFAULT nextval('public.user_id_seq');

ALTER TABLE ONLY public.manager ALTER COLUMN id SET DEFAULT nextval('public.user_id_seq');

ALTER TABLE ONLY public.medkit ALTER COLUMN id SET DEFAULT nextval('public.medkit_id_seq');

ALTER TABLE ONLY public.medkitcontent ALTER COLUMN id SET DEFAULT nextval('public.medkitcontent_id_seq');

ALTER TABLE ONLY public.photo ALTER COLUMN id SET DEFAULT nextval('public.photo_id_seq');

ALTER TABLE ONLY public.request ALTER COLUMN id SET DEFAULT nextval('public.request_id_seq');

ALTER TABLE ONLY public.storage ALTER COLUMN id SET DEFAULT nextval('public.storage_id_seq');

ALTER TABLE ONLY public.tab ALTER COLUMN id SET DEFAULT nextval('public.tab_id_seq');

ALTER TABLE ONLY public.transferlog ALTER COLUMN id SET DEFAULT nextval('public.transferlog_id_seq');

ALTER TABLE ONLY public."user" ALTER COLUMN id SET DEFAULT nextval('public.user_id_seq');

ALTER TABLE ONLY public.act
    ADD CONSTRAINT act_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.administrator
    ADD CONSTRAINT administrator_email_key UNIQUE (email);

ALTER TABLE ONLY public.manager
    ADD CONSTRAINT manager_email_key UNIQUE (email);

ALTER TABLE ONLY public.medkit
    ADD CONSTRAINT medkit_number_key UNIQUE (number);

ALTER TABLE ONLY public.medkit
    ADD CONSTRAINT medkit_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.medkitcontent
    ADD CONSTRAINT medkitcontent_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.photo
    ADD CONSTRAINT photo_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.request
    ADD CONSTRAINT request_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.storage
    ADD CONSTRAINT storage_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.tab
    ADD CONSTRAINT tab_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.transferlog
    ADD CONSTRAINT transferlog_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public."user"
    ADD CONSTRAINT user_login_key UNIQUE (login);

ALTER TABLE ONLY public."user"
    ADD CONSTRAINT user_pkey PRIMARY KEY (id);

ALTER TABLE ONLY public.medkit
    ADD CONSTRAINT medkit_storage_id_fkey FOREIGN KEY (storage_id) REFERENCES public.storage(id) ON DELETE SET NULL;

ALTER TABLE ONLY public.medkit
    ADD CONSTRAINT medkit_tab_id_fkey FOREIGN KEY (tab_id) REFERENCES public.tab(id) ON DELETE SET NULL;

ALTER TABLE ONLY public.medkitcontent
    ADD CONSTRAINT medkitcontent_act_id_fkey FOREIGN KEY (act_id) REFERENCES public.act(id) ON DELETE CASCADE;

ALTER TABLE ONLY public.medkitcontent
    ADD CONSTRAINT medkitcontent_medkit_id_fkey FOREIGN KEY (medkit_id) REFERENCES public.medkit(id) ON DELETE CASCADE;

ALTER TABLE ONLY public.medkitcontent
    ADD CONSTRAINT medkitcontent_photo_id_fkey FOREIGN KEY (photo_id) REFERENCES public.photo(id) ON DELETE CASCADE;

ALTER TABLE ONLY public.request
    ADD CONSTRAINT request_medkitnumber_fkey FOREIGN KEY (medkitnumber) REFERENCES public.medkit(id) ON DELETE CASCADE;

ALTER TABLE ONLY public.transferlog
    ADD CONSTRAINT transferlog_medkit_id_fkey FOREIGN KEY (medkit_id) REFERENCES public.medkit(id) ON DELETE CASCADE;
