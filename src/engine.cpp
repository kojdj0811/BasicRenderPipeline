#include "engine.h"

Engine* Engine::m_instance;

Engine::Engine(int a_width, int a_height, const char* a_windowName)
{
    if(m_instance != nullptr) return;
    this->screenWidth = a_width;
    this->screenHeight = a_height;
    this->windowName = a_windowName;

    mouseInput = new MouseInput();

    m_instance = this;
}

Engine::~Engine () {
    SAFE_DELETE(mouseInput);
    SAFE_DELETE(m_cameraController);
    SAFE_DELETE(m_rendererEntity);
    printf("Engine is shutdown\n");
}


Engine* Engine::GetInstance () {
    return m_instance;
}


void Engine::errorCallback (int errorCode, const char* errorDescription) {
    fprintf(stderr, "Error(%d): %s\n", errorCode, errorDescription);
}

void WindowResizeCallBack(GLFWwindow* a_window, int a_width, int a_height)
{
    glViewport(0, 0, a_width, a_height);
    fprintf(stderr, "WindowResized :: (%d, %d)\n", a_width, a_height);
    // TODO: Do your resize logic here...
}

void Engine::InitializeUiSystem() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}


int Engine::Initialize()
{
    glfwSetErrorCallback(errorCallback);

    // Initialize GLFW.
    glfwInit();

    // Tell GLFW that we want to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Tell GLFW that we want to use the OpenGL's core profile.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Do this for mac compatability.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //anti aliasing
    glfwWindowHint(GLFW_SAMPLES, 4);


    // Create Window.

    // Instantiate the window object.
    this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, this->windowName, NULL, NULL);

    // Make sure that the window is created.
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();

        std::cin.get();
        return 0;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize GLAD.

    // Make sure that glad has been initialized successfully.
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        
        std::cin.get();
        return 0;
    }


    // error
    std::cout << "OpenGL version" << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vender" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer" << glGetString(GL_RENDERER) << std::endl;
    std::cout << std::endl;



    // Set the viewport
    glViewport(0, 0, this->screenWidth, this->screenHeight);

    // Setup callbacks.

    // Binds the 'framebuffer_size_callback' method to the window resize event.
    glfwSetFramebufferSizeCallback(window, WindowResizeCallBack);

    this->InitializeUiSystem();

    this->SetupOpenGlRendering();
    this->InitializeSceneObjects();
    this->SetupRenderingData();


    // Start game loop.
    while(!glfwWindowShouldClose(this->window))
    {
        // Calculate the elapsed time between the current and previous frame.
        float m_frameTime = (float)glfwGetTime();
        float m_deltaTime = m_frameTime - this->lastFrameTime;
        this->lastFrameTime = m_frameTime;


        fps++;
        if(m_frameTime - lastFpsTime >= 1.0f) {
            fprintf(stderr, "%.4f ms/frame %d fps\n", 1000.0/fps, fps);
            fps = 0;
            lastFpsTime = m_frameTime;
        }





        glfwPollEvents();
        this->ProcessInput(this->window);

        glClearColor(this->clearColor.x, this->clearColor.y, this->clearColor.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Application logic
        this->Update(m_deltaTime);
        this->Draw();

        this->UpdateUiSystem();

        glfwSwapBuffers(this->window);
    }




    glUseProgram(0);
    glBindVertexArray(0);


    m_rendererEntity->ReadyToShutdown();
    this->Shutdown();

    glfwTerminate();

    return 1;
}


void MouseButtonCallback (GLFWwindow* window, int button, int action, int mods) {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

    MouseInput* _mouseInput = Engine::GetInstance()->mouseInput;
    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT: {
            _mouseInput->UpdateCurrentMouseButtonState(window, action, _mouseInput->leftButton);
            break;
        }

        case GLFW_MOUSE_BUTTON_MIDDLE: {
            _mouseInput->UpdateCurrentMouseButtonState(window, action, _mouseInput->middleButton);
            break;
        }

        case GLFW_MOUSE_BUTTON_RIGHT: {
            _mouseInput->UpdateCurrentMouseButtonState(window, action, _mouseInput->rightButton);
            break;
        }

        default: {
            fprintf(stderr, "Unknown Mouse Button\n");
            break;
        }
    }
}

void CursorPositionCallback (GLFWwindow* window, double xpos, double ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

    MouseInput* _mouseInput = Engine::GetInstance()->mouseInput;
    _mouseInput->UpdateScreenPosition(window);

    if(_mouseInput->rightButton->IsDrag()) {
        //rotate camera
        glm::vec2 deltaPosition = _mouseInput->GetScreenDeltaPosition();
        
    }
}


void Engine::ProcessInput(GLFWwindow* a_window)
{
    // TODO: Process your input here...

    // If the escape key gets pressed, close the window.
    if(glfwGetKey(a_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(a_window, true);

    if(glfwGetKey(a_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        m_cameraController->SetPosition(m_cameraController->GetPosition() - glm::vec3(0.1f, 0.0f, 0.0f));
    }

    if(glfwGetKey(a_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        m_cameraController->SetPosition(m_cameraController->GetPosition() + glm::vec3(0.1f, 0.0f, 0.0f));
    }

    glfwSetWindowFocusCallback(window, ImGui_ImplGlfw_WindowFocusCallback);
    glfwSetCursorEnterCallback(window, ImGui_ImplGlfw_CursorEnterCallback);
    // glfwSetCursorPosCallback(window, ImGui_ImplGlfw_CursorPosCallback);
    // glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
    glfwSetScrollCallback(window, ImGui_ImplGlfw_ScrollCallback);
    glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
    glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
    glfwSetMonitorCallback(ImGui_ImplGlfw_MonitorCallback);


    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
}



void Engine::SetupOpenGlRendering()
{
    // TODO: Setup OpenGL code here...
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

}

void Engine::SetupRenderingData () {
    m_rendererEntity->SetupRenderingData();
}


void Engine::InitializeSceneObjects () {
    m_cameraController = new CameraController(glm::vec3(4.0f, 3.0f, 3.0f));
    m_cameraController->LookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    m_rendererEntity = new SingleQuadRenderer(m_cameraController->GetMvpMatrix(glm::mat4(1.0f)));
}

void Engine::Update(float a_deltaTime)
{
    // TODO: Update your logic here...
    m_rendererEntity->Update(a_deltaTime);

    m_rendererEntity->SetMvpMatrix(m_cameraController->GetMvpMatrix(glm::mat4(1.0f)));
}

void Engine::UpdateUiSystem() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::ShowDemoWindow();
    ImGui::ShowMetricsWindow();
    // ImGui::ShowUserGuide();
    // ImGui::GetVersion();

    ImGui::Begin("My Window");
    static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

    if (ImGui::BeginTable("Camera View Matrix", 4, flags))
    {
        ImGui::TableSetupColumn("(0, n)", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("(1, n)", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("(2, n)", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("(3, n)", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableHeadersRow();
        glm::mat4 cameraViewMatrix = m_cameraController->GetViewMatrix();
        for (int row = 0; row < 4; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 4; column++)
            {
                ImGui::TableSetColumnIndex(column);
                // ImGui::Text("(%d,%d) %f", column, row, cameraViewMatrix[column][row]);
                ImGui::Text("%f", cameraViewMatrix[column][row]);
            }
        }
        ImGui::EndTable();
    }
    if (ImGui::BeginTable("table2", 6, flags))
    {
        ImGui::TableSetupColumn("AAA", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("BBB", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("CCC", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultHide);
        ImGui::TableSetupColumn("DDD", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("EEE", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("FFF", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultHide);
        ImGui::TableHeadersRow();
        for (int row = 0; row < 5; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 6; column++)
            {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%d,%d", column, row);
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();



    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void Engine::Draw()
{
    // TODO: Render your stuff here...
    m_rendererEntity->Draw();
}

void Engine::Shutdown () {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}



glm::ivec2 Engine::GetScreenSize() {
    return glm::ivec2(screenWidth, screenHeight);
}