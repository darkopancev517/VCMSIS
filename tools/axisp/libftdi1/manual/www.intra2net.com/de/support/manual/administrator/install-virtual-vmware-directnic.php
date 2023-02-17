<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Virtuelle Maschine mit direktem Internetzugang | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="install-virtual-vmware.php" title="5. Kapitel - Installation auf VMware vSphere Hypervisor 4 (ESXi)"><link rel="prev" href="install-virtual-vmware.php" title="5. Kapitel - Installation auf VMware vSphere Hypervisor 4 (ESXi)"><link rel="next" href="install-virtual-vmware-install.php" title="5.3. Installation des Intranators">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="install-virtual-vmware-directnic.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="install-virtual-vmware-directnic.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">5.2. Virtuelle Maschine mit direktem Internetzugang</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="install-virtual-vmware.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">5. Kapitel - Installation auf VMware vSphere Hypervisor 4 (ESXi)</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="install-virtual-vmware-install.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="install-virtual-vmware-directnic"></a>5.2. Virtuelle Maschine mit direktem Internetzugang</h2></div></div></div><a class="indexterm" name="install-virtual-vmware-directnic-firewall"></a><a class="indexterm" name="install-virtual-vmware-directnic-vmdirectpath"></a><p>Wie in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="install-virtual.php#install-virtual-real-directnic">Abschnitt&nbsp;4.1.3, &#8222;Kontakt mit ungefilterten Netzwerkpaketen&#8220;</a> beschrieben, empfehlen wir, Netzwerkkarten, die direkt mit dem Internet verbunden
            sind, als komplette PCI-Ger&auml;te an die VM durchzureichen.</p><p>Diese Funktionalit&auml;t wird VMDirectPath genannt und ben&ouml;tigt die Unterst&uuml;tzung durch
            Prozessor, Mainboard und BIOS. Von Intel wird dies VT-d genannt, bei AMD hei&szlig;t es AMD-Vi
            oder IOMMU. Diese Funktionen sind meist nur bei Serversystemen implementiert, bei f&uuml;r
            den Desktop-Einsatz konzipierten Rechnern fehlt h&auml;ufig eine vollst&auml;ndige Unterst&uuml;tzung
            durch alle Komponenten. Weitere Informationen dazu finden Sie bei VMware und Ihrem
            Hardwarehersteller.</p><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="d0e831"></a>5.2.1. Vorbereitung des Servers</h4></div></div></div><p>Bevor eine Netzwerkkarte direkt an eine VM &uuml;bergeben werden kann, muss Sie im
                VMware-Server freigegeben werden:</p><div class="orderedlist"><ol type="1"><li><p>Starten Sie den vSphere Client und verbinden sich mit dem ESXi-Server.
                        W&auml;hlen Sie links den Server selbst aus und &ouml;ffnen das Men&uuml;
                            <span class="guimenu">Konfiguration</span>. </p><div class="mediaobject"><img src="../images/install/vmware/vmware-passthrough-server-01.png"></div></li><li><p>Klicken Sie auf <span class="guibutton">Passthrough konfigurieren</span> und
                        w&auml;hlen die entsprechende Netzwerkkarte samt zugeh&ouml;riger Bridge aus.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-passthrough-server-02.png"></div></li><li><p>Die Netzwerkkarte steht nach einem Neustart des VMware-Servers f&uuml;r
                        VMDirectPath zur Verf&uuml;gung.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-passthrough-server-03.png"></div></li></ol></div></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="d0e861"></a>5.2.2. Einbinden der Netzwerkkarte in die VM</h4></div></div></div><p>Die Netzwerkkarte kann nun wie folgt eingebunden werden:</p><div class="orderedlist"><ol type="1"><li><p>&Ouml;ffnen Sie die Konfiguration der VM und klicken im Men&uuml;
                            <span class="guimenu">Hardware</span> auf
                        <span class="guibutton">Hinzuf&uuml;gen</span>.</p></li><li><p>F&uuml;gen Sie ein PCI-Ger&auml;t hinzu.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-passthrough-vm-01.png"></div></li><li><p>W&auml;hlen Sie die vorhin freigegebene Netzwerkkarte aus und Schlie&szlig;en das
                        Hinzuf&uuml;gen ab.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-passthrough-vm-02.png"></div></li><li><p>Die Netzwerkkarte wird jetzt als zus&auml;tzliches Ger&auml;t angezeigt.</p><div class="mediaobject"><img src="../images/install/vmware/vmware-passthrough-vm-03.png"></div></li></ol></div><a class="indexterm" name="d0e894"></a><a class="indexterm" name="d0e895"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="install-virtual-vmware.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="install-virtual-vmware.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="install-virtual-vmware-install.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">5. Kapitel - Installation auf VMware vSphere Hypervisor 4 (ESXi)&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;5.3. Installation des Intranators</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>